/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 *
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Boss_Vectus
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SPELL_FLAMESTRIKE            = 18399,
    SPELL_BLAST_WAVE             = 16046,
};

class boss_vectus : public CreatureScript
{
public:
    boss_vectus() : CreatureScript("boss_vectus") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_vectusAI (pCreature);
    }

    struct boss_vectusAI : public ScriptedAI
    {
        boss_vectusAI(Creature *c) : ScriptedAI(c) {}

        
        uint32 BlastWave_Timer;
        uint32 FlameStrike_Timer;

        void Reset()
        {
            FlameStrike_Timer = 5000;
			BlastWave_Timer = 10000;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            //BlastWave_Timer
            if (BlastWave_Timer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_BLAST_WAVE);
                BlastWave_Timer = 12000;
            }
            else
                BlastWave_Timer -= Diff;

            //FlameStrike_Timer
			if(FlameStrike_Timer<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_FLAMESTRIKE);
                FlameStrike_Timer = 18000;
            } else FlameStrike_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_vectus()
{
    new boss_vectus();
}